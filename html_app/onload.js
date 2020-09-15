let config = {}
let arrays = {}

function moduleTitle(text) {
  const title = document.createElement('h3')
  title.setAttribute('class', 'module_title')
  title.innerText = text
  return title
}

function arrayTitle(text, onShowHide) {
  const body = document.createElement('div')
  body.setAttribute('class', 'array_title')
  const title = document.createElement('h2')
  title.innerText = text
  body.appendChild(title)
  const expand = document.createElement('a')
  expand.innerText = 'show/hide'
  expand.setAttribute('href', 'javascript:void(0)')
  expand.addEventListener('click', onShowHide)
  body.appendChild(expand)
  return body
}

function renderField(title, field) {
  const body = document.createElement('div')

  const label = document.createElement('label')
  label.innerText = title
  body.appendChild(label)

  const error = document.createElement('div')
  error.setAttribute('class', 'error')

  let setValue, currentValue
  const fetchField = () => {
    fetchParam(field.type.charAt(0), field.caps_name)
    .then(v => {
      currentValue = v
      setValue(v)
      body.setAttribute('class', body.getAttribute('class').replace('loading', ''))
      error.innerText = ''
    })
    .catch((e) => {
      error.innerText = `Failed to load ${field.name}`;
    })
  }
  
  if (field.write && !field.indir) {
    body.setAttribute('class', 'field')
    const input = document.createElement('input')
    input.setAttribute('class', 'value')
    input.addEventListener('keyup', (e) => {
      let value = e.target.value
      if (field.type == 'integer') {
        value = parseInt(e.target.value)
        if (isNaN(value)) {
          return
        }
      }
      if (e.keyCode == 13) {
        body.setAttribute('class', 'field loading')
        updateParam(field.type.charAt(0), field.caps_name, value)
          .then(() => {
            body.setAttribute('class', 'field')
            fetchField()
            error.innerText = ''
          })
          .catch(() => {
            error.innerText = `Failed to update ${field.name}`
          })
      } else {
        error.innerText = ''
        if (currentValue != value) {
          body.setAttribute('class', 'field modified')
        } else {
          body.setAttribute('class', 'field')
        }
      }
    })
    body.appendChild(input)
    setValue = (v) => {input.value = v}
  } else if (field.write && field.indir) {
    body.setAttribute('class', 'field')
    const input = document.createElement('select')
    input.setAttribute('class', 'value')
    input.addEventListener('change', (e) => {
      body.setAttribute('class', 'field loading')
        updateParam(field.type.charAt(0), field.caps_name, e.target.value)
          .then(() => {
            body.setAttribute('class', 'field')
            fetchField()
            error.innerText = ''
          })
          .catch(() => {
            error.innerText = `Failed to update ${field.name}`
          })
        })
    const opt = document.createElement('option')
    opt.value = 0
    opt.innerText = 'Disabled'
    input.appendChild(opt)
    field.indir.values.forEach((i, index) => {
      const opt = document.createElement('option')
      opt.value = i
      opt.innerText = field.indir.helpers[index] || i
      input.appendChild(opt)
    })
    body.appendChild(input)
    setValue = (v) => {input.value = v}
  } else {
    body.setAttribute('class', 'field ro')
    const value = document.createElement('div')
    value.setAttribute('class', 'value')
    value.setAttribute('id', field.name)
    body.appendChild(value)
    setValue = (v) => {value.innerText = v}
  }
  body.appendChild(error)
  body.setAttribute('class', body.getAttribute('class') + ' loading')
  fetchField()
  return body
}

function renderModule(title, module, in_array) {
  const body = document.createElement('div')
  body.setAttribute('class', 'module')

  if (title) {
    body.appendChild(moduleTitle(title))
  }

  const fields = document.createElement('div')
  fields.setAttribute('class', 'fields')
  Object.keys(module).sort((m1, m2) => {
    if (module[m1].write && !module[m2].write) {
      return 1
    } else if (module[m2].write && !module[m1].write) {
      return -1
    }
    return m1.localeCompare(m2)
  }).forEach(f => {
    const field = document.createElement('div')
    let name = f
    if (in_array) {
      name = f.split('_').splice(2).join('_')
    } else if (f.indexOf(`${module[f].module}_`) == 0) {
      name = f.replace(new RegExp(`^${module[f].module}_`), '')
    }
    field.appendChild(renderField(name, module[f]))
    fields.appendChild(field)
  })
  body.appendChild(fields)
  return body
}

function renderModules(modules, array) {
  const body = document.createElement('div')
  Object.keys(modules).sort((m1, m2) => {
    if (m1 == array) {
      return -1
    } else if (m2 == array) {
      return 1
    }
    return m1.localeCompare(m2)
  }).forEach(m => {
    body.appendChild(renderModule(m == array ? '' : m, modules[m], !!array))
  })
  return body
}

function renderPagination(n, onSelect) {
  const body = document.createElement('div')
  body.setAttribute('class', 'pagination')

  const links = []
  for (let i = 0; i < n; ++i) {
    const a = document.createElement('a')
    links.push(a)
    const isel = i
    a.innerText = i+1
    a.setAttribute('href', 'javascript:void(0)')
    a.addEventListener('click', () => {
      links.forEach(l => l.setAttribute('class', ''))
      a.setAttribute('class', 'selected')
      onSelect(isel)
    }, false);
    body.appendChild(a)
  }
  links[0].setAttribute('class', 'selected')
  return body
}

function renderArray(title, array) {
  let shown = false;
  const body = document.createElement('div')
  const container = document.createElement('div')
  container.setAttribute('class', 'array_container')

  const render = () => {
    const modules = document.createElement('div')
    modules.appendChild(renderModules(array[0].modules, title))
    container.appendChild(modules)

    container.appendChild(renderPagination(array.length, (i) => {
      while (modules.firstChild) modules.removeChild(modules.firstChild)
      modules.appendChild(renderModules(array[i].modules, title))
    }))
  }

  body.appendChild(arrayTitle(title, () => {
    shown = !shown
    if (shown) {
      render()
    } else {
      while (container.firstChild) container.removeChild(container.firstChild)
    }
  }))
  body.appendChild(container)
  return body
}

function renderParams(data) {
  const body = document.createElement('div')
  body.setAttribute('class', 'params')

  Object.keys(data).sort((d1, d2) => {
    if (data[d1].array) {
      return 1
    } else if (data[d2].array) {
      return -1
    }
    return d1.localeCompare(d2)
  }).forEach(d => {
    if (data[d].array) {
      body.appendChild(renderArray(d, data[d].array))
    } else {
      body.appendChild(renderModules(data[d].modules))
    }
  })
  return body
}

function renderTopMenuItem(id, title, onSelect) {
  const body = document.createElement('div')
  body.setAttribute('class', `menu_item_${id}`)
  body.innerText = title
  body.addEventListener('click', onSelect)
  return body
}

function renderTopMenu(onSelect) {
  const body = document.createElement('div')
  body.setAttribute('class', 'menu modules')
  body.appendChild(renderTopMenuItem('modules', config.name, () => {
    body.setAttribute('class', 'menu modules')
    onSelect('modules')
  }))
  body.appendChild(renderTopMenuItem('system', 'System', () => {
    body.setAttribute('class', 'menu system')
    onSelect('system')
  }))
  document.body.appendChild(body)
}

async function start() {
  config = await fetchConfig()
  modules = config.keys.reduce((acc, k) => {
    const d = acc[k.core ? 'system' : 'modules']
    const n = (k.array ? k.array.name : k.module)
    if (k.array) {
      const i = parseInt(k.name.split('_')[1])
      d[n] = d[n] || {array: []}
      d[n].array[i] = d[n].array[i] || {modules: {}}
      d[n].array[i].modules[k.module] = d[n].array[i].modules[k.module] || {}
      d[n].array[i].modules[k.module][k.name] = k
    } else {
      d[n] = d[n] || {modules: {}}
      d[n].modules[k.module] = d[n].modules[k.module] || {}
      d[n].modules[k.module][k.name] = k
    }
    return acc
  }, {system: {}, modules: {}})

  const params = document.createElement('div')
  renderTopMenu((s) => {
    while (params.firstChild) params.removeChild(params.firstChild)
    params.appendChild(renderParams(modules[s]))
  })
  params.appendChild(renderParams(modules.modules))
  document.body.appendChild(params)
}

window.onload = () => {
  start()
}
