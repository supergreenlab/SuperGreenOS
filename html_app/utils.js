const URL = 'http://192.168.1.11'
const DEBUG = false

const schedule_promise = (n, retries) => {
  let loading_param_promise = Promise.resolve(),
      promises = []
  return function(req_func, ret_func) {
    let resolve, reject
    const p = new Promise((res, rej) => {resolve = res; reject = rej})
    loading_param_promise.then(async () => {
      let error
      for (let i = 0; i < retries; ++i) {
        try {
          resolve(await req_func())
          return
        } catch(e) {
          error = e
          if (e.status == 404) {
            break
          }
          ret_func && ret_func(e, i + 1)
        }
      }
      reject(error)
    })
    promises.push(p)
    if (promises.length >= n) {
      loading_param_promise = Promise.all(promises).catch((e) => {
        console.log('promise.all', e)
      })
      promises = []
    }

    return p
  }
}
const fetchQueue = schedule_promise(3, 3)

const fetchConfig = async function() {
  return new Promise(function(resolve, reject) {
    const r = new XMLHttpRequest()
    r.open('GET', DEBUG ? '/config.json' : '/fs/config.json', true)
    r.onreadystatechange = function () {
      if (r.readyState != 4) return
      if (r.status != 200) {
        reject(r.status, r.responseText)
        return
      }
      resolve(JSON.parse(r.responseText))
    }
    r.send()
  })
}

const fetchParam = async function(type, paramName) {
  return fetchQueue(() => new Promise(function(resolve, reject) {
    const r = new XMLHttpRequest()
    r.open('GET', `${DEBUG ? URL : ''}/${type}?k=${paramName}`, true)
    r.onreadystatechange = function () {
      if (r.readyState != 4) return
      if (r.status != 200) {
        reject(r.status, r.responseText)
        return
      }
      if (type == 'i') {
        resolve(parseInt(r.responseText))
      } else {
        resolve(r.responseText);
      }
    }
    r.send()
  }))
}

const updateParam = async function(type, paramName, value) {
  return fetchQueue(() => new Promise(function(resolve, reject) {
    const r = new XMLHttpRequest()
    r.open('POST', `${DEBUG ? URL : ''}/${type}?k=${paramName}&v=${encodeURIComponent(value)}`, true)
    r.onreadystatechange = function () {
      if (r.readyState != 4) return
      if (r.status != 200) {
        reject(r.status, r.responseText)
        return
      }
      resolve(r.responseText);
    }
    r.send()
  }))
}
