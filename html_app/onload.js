let config = {}
let arrays = {}

function sectionTitle(text) {
  const title = document.createElement('h1')
  title.setAttribute('class', 'section_title')
  title.innerText = text
  return title
}

function moduleTitle(text) {
  const title = document.createElement('h2')
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
  body.setAttribute('class', 'field')

  const label = document.createElement('label')
  label.innerText = title
  body.appendChild(label)

  if (field.write) {
    const input = document.createElement('input')
    input.setAttribute('id', field.name)
    body.appendChild(input)
  } else {
    const value = document.createElement('div')
    value.setAttribute('id', field.name)
    body.appendChild(value)
  }
  return body
}

function renderModule(title, module) {
  const body = document.createElement('div')
  body.appendChild(moduleTitle(title))
  body.setAttribute('class', 'module')

  const fields = document.createElement('div')
  fields.setAttribute('class', 'fields')
  Object.keys(module).sort((m1, m2) => {
    if (module[m1].write) {
      return 1
    } else if (module[m2].write) {
      return 1
    }
    return m1.localeCompare(m2)
  }).forEach(f => {
    const field = document.createElement('div')
    field.appendChild(renderField(f, module[f]))
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
    body.appendChild(renderModule(m, modules[m]))
  })
  return body
}

function renderPagination(n, onSelect) {
  const body = document.createElement('div')
  body.setAttribute('class', 'pagination')

  for (let i = 0; i < n; ++i) {
    const a = document.createElement('a')
    const isel = i
    a.innerText = i+1
    a.setAttribute('href', 'javascript:void(0)')
    a.addEventListener('click', () => onSelect(isel), false);
    body.appendChild(a)
  }
  return body
}

function renderArray(title, array) {
  let shown = false;
  const body = document.createElement('div')
  const container = document.createElement('div')

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

function renderParams(title, data) {
  const body = document.createElement('div')
  body.setAttribute('class', 'params')
  body.appendChild(sectionTitle(title))

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

  renderParams(config.name, modules.modules)
  renderParams('System', modules.system)
}

window.onload = () => {
  start()
}
