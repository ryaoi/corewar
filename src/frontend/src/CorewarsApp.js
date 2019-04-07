import React from 'react'
import PlayerUploadForm from './PlayerUploadForm'
import GameComponent from './GameComponent'

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
		alert('Somehow got a response:')
		this.setState({game_id: "example-id"})
		return response
	}
	render() {
		if (!this.state.game_id)
			return (
				<PlayerUploadForm parent={this}/>
			)
		else
			return (
				<GameComponent game_id={this.state.game_id}/>
			)
	}
}

export default CorewarsApp;
export { handleErrors }
