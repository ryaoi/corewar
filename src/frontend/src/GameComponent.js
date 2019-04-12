import React, { Component } from 'react'
import { createStore } from 'redux'
import { Provider } from 'react-redux'
import rootReducer from './redux/Reducers'
import LogBarContainer from './LogBar'
import './style/index.css'
import './style/game.css'

const store = createStore(rootReducer)

class GameComponent extends Component {
	componentDidMount () {
		this.updateLogs()
	}
	updateLogs() {
		console.log('Updating logs but not really')
		var example_line = [{
			text: "example text",
			type: 1
		}]
		store.dispatch({type: 'ADD_LINES', input: example_line})
	}
	render () {
		return (
			<Provider store={store}>
			<div className="game-component">
				<div className="game-pane">
					<div className="game-top-bar">
						placeholder
					</div>
					<div className="game-mem-dump">
						placeholder
					</div>
				</div>
				<LogBarContainer/>
			</div>
			</Provider>
		);
	}
}

export default GameComponent
