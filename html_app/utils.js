const URL = 'http://192.168.1.11'

const fetchConfig = async function() {
  return new Promise(function(resolve, reject) {
    const r = new XMLHttpRequest()
    r.open('GET', `config.json?id=${parseInt(Math.random()*999999)}`, true)
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
  return new Promise(function(resolve, reject) {
    const r = new XMLHttpRequest()
    r.open('GET', `${URL}/${type}?k=${paramName}`, true)
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
  })
}

const updateParam = async function(type, paramName, value) {
  return new Promise(function(resolve, reject) {
    const r = new XMLHttpRequest()
    r.open('POST', `${URL}/${type}?k=${paramName}&v=${value}`, true)
    r.onreadystatechange = function () {
      if (r.readyState != 4) return
      if (r.status != 200) {
        reject(r.status, r.responseText)
        return
      }
      resolve(r.responseText);
    }
    r.send()
  })
}

const updateDiv = function(id, value) {
  document.getElementById(id).innerText = value
}
