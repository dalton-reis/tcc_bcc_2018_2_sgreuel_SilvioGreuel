import { getJwt } from './jwt'

export const getBearerJwt = () => (`Bearer ${getJwt()}`)

//export const getUrl = (path) => (`https://localhost:44347${path}`)
export const getUrl = (path) => (`https://api.greuel.com.br${path}`)
// export const getUrl = (path) => (`https://localhost:44347`)

export const post = (path, body) => fetch(getUrl(path), {
        mode: "cors",
        method: "POST",
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json',
          'Authorization': getBearerJwt()
        },
        body: JSON.stringify(body)
      })

export const get = (path) => fetch(getUrl(path), {
        mode: "cors",
        method: "GET",
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json',
          'Authorization': getBearerJwt() 
        }
      })

export const del = (path) => fetch(getUrl(path), {
        mode: "cors",
        method: "DELETE",
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json',
          'Authorization': getBearerJwt() 
        }
      })