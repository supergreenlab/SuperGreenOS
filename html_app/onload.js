let config = {}

async function start() {
  config = await fetchConfig()
  const arrays = config.keys.reduce((acc, k) => {
    const n = k.array ? k.array.name : 'global'
    acc[n] = acc[n] || {fields: {}, core: k.core}
    acc[n].fields[k.name] = k
    return acc
  }, {})
  console.log(arrays)
}

window.onload = () => {
  start()
}
