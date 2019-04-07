import React, { Component } from 'react'
import './index.css'
import './game.css'

class LogPane extends Component {
	constructor (props) {
		super(props)
		this.relevant_logs_updated = false
	}
	renderLine() {
		return (
			<div>line placeholder</div>
		)
	}
	shouldComponentUpdate(nextProps) {
		if (this.props.log_conf !== nextProps.log_conf
			|| this.relevant_logs_updated)
			return true
		return false
	}
	render () {
		return (
			<div className="game-log-pan">
				{this.props.log_cache.map(() => this.renderLine())}
			</div>
		)
	}
}

class GameComponent extends Component {
	constructor (props) {
		super(props)
		this.state = {log_pane_conf: [[1, 6, 7]],
			log_cache: [],
			log_updated_channels: [1]
		}
	}
	componentDidMount () {
		this.inverval = setInterval(() => this.updateLogs(), 500)
	}
	updateLogs() {
		console.log('Updating logs but not really')
		/* TODO fetch new logs, check new used log channels and update accordingly */

		this.setState(function(prevState) {
			var newState = prevState
			newState.log_cache = [...newState.log_cache, "message"]
			return newState
		})
	}
	renderLog (item, i) {
		return (
			<LogPane key={i} log_conf={item} log_cache={this.state.log_cache}/>
		)
	}
	render () {
		return (
			<div className="game-component">
				<div className="game-top-bar">
					placeholder
				</div>
				<div className="game-container">
					<div className="game-mem-dump">
						placeholder
					</div>
					<div className="game-logs">
						{this.state.log_pane_conf.map((item, i) => this.renderLog(item, i))}
					</div>
				</div>
			</div>
		);
	}
}

export default GameComponent;
