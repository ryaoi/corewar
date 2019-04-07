import React from 'react'
import PlayerUploadForm from './PlayerUploadForm'
import GameComponent from './GameComponent'

class CorewarsApp extends React.Component {
	constructor() {
		super()
		this.state = {is_playing: false}
		this.game_id = null;
	}
	render() {
		if (!this.game_id)
			return (
				<PlayerUploadForm parent={this}/>
			)
		else
			return (
				<GameComponent/>
			)
	}
}

export default CorewarsApp;
