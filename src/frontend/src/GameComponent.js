import React, { Component } from 'react'
import { createStore } from 'redux'
import { Provider } from 'react-redux'
import rootReducer from './redux/Reducers'
import LogBarContainer from './LogBar'
import MemDumpView from './MemDumpView'
import './style/index.css'
import './style/game.css'

const store = createStore(rootReducer)

class GameComponent extends Component {
	constructor (props) {
		super(props)
		this.time_updated = new Date().getTime()
	}
	componentDidMount () {
		this.fetch_timeout = setTimeout(this.tryFetch.bind(this), 500)
	}
	componentWillUnmount () {
		if (this.fetch_timeout)
			clearTimeout(this.fetch_timeout)
	}
	handleFetchTimeout () {
		const elapsed = (new Date().getTime()) - this.time_updated
		const to_wait = Math.max(0, 500 - elapsed)
		this.fetch_timeout = setTimeout(this.tryFetch.bind(this), to_wait)
	}
	tryFetch () {
		console.log('Fetching data')
		const request_body = {
			game_id: this.props.game_id,
			cycles: 1,
			logs_nbr: [1, 6, 7]
		}
		this.time_updated = new Date().getTime()
		fetch('http://localhost:3000/AJAX/update', {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json'
			},
			body: JSON.stringify(request_body),
		}).then((response) => response.json())
		.then((data) => console.log(data) /* TODO put through reducer */)
		.then(this.handleFetchTimeout.bind(this))
		.catch((error) => console.error(error))
	}
	render () {
		return (
			<Provider store={store}>
			<div className="game-component">
				<div className="game-pane">
					<div className="game-top-bar">
						placeholder
					</div>
					<MemDumpView/>
				</div>
				<LogBarContainer/>
			</div>
			</Provider>
		);
	}
}

export default GameComponent
