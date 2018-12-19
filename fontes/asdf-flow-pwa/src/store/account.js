export default {
  state: {
      token: null,
      name: null
  },
  mutations: {
    ['account/signin'] (state, {token, name}) {
        state.token = token;
        state.name = name;
    }
  },
  actions: {
      signin ({ commit }, {user, pin}) {
          commit('account/signin', {user, token: pin})
      }
  },
} 