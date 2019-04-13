import React, { Component } from 'react'
import { connect } from 'react-redux'
import { handleErrors } from './CorewarsApp'
import LogBarContainer from './LogBar'
import MemDumpView from './MemDumpView'
import './style/index.css'
import './style/game.css'

class GameComponent extends Component {
	constructor (props) {
		super(props)
		this.time_updated = new Date().getTime()
		this.state = {}
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
	handleUpdate (response) {
		this.setState({
			mem_dump: response.mem
		})
		this.props.dispatchLogs(response.log)
	}
	tryFetch () {
		console.log('Fetching data')
		const request_body = {
			game_id: this.props.game_id,
			cycles: 100,
			active_logs: [1, 6, 7]
		}
		this.time_updated = new Date().getTime()
		fetch('http://localhost:3000/AJAX/update', {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json'
			},
			body: JSON.stringify(request_body),
		}).then(handleErrors)
		.then((response) => response.json())
		.then(this.handleUpdate.bind(this))
		.then(this.handleFetchTimeout.bind(this))
		.catch((error) => console.error(error))
	}
	render () {
		return (
			<div className="game-component">
				<div className="game-pane">
					<div className="game-top-bar">
						placeholder
					</div>
					<MemDumpView mem_dump={this.state.mem_dump}/>
				</div>
				<LogBarContainer/>
			</div>
		);
	}
}

const GameComponentContainer = connect(
	null,
	(dispatch) => ({
		dispatchLogs: (logs) => dispatch({type: 'ADD_LINES', input: logs})
	})
)(GameComponent)

export default GameComponentContainer
