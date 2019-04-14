import React from 'react'
import { createStore } from 'redux'
import { Provider } from 'react-redux'
import rootReducer, { initial_state } from './redux/Reducers'
import PlayerUploadForm from './PlayerUploadForm'
import GameComponent from './GameComponent'

const store = createStore(rootReducer, initial_state)

function handleErrors(response) {
	if (!response.ok)
		throw Error(response.statusText)
	return response
}

class CorewarsApp extends React.Component {
	constructor(props) {
		super(props)
		this.state = {game_id: null}
	}
	gameStarted (response) {
		if (response.length > 300)
			throw Error("game_id too long")
		this.setState({game_id: response})
		return response
	}
	render() {
		if (!this.state.game_id)
			return (
				<PlayerUploadForm parent={this}/>
			)
		else
			return (
				<Provider store={store}>
					<GameComponent game_id={this.state.game_id}/>
				</Provider>
			)
	}
}

export default CorewarsApp;
export { handleErrors }
