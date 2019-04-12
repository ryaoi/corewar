import React, { Component } from 'react'
import './style/index.css'
import './style/game.css'

class LogLine extends Component {
	render () {
		return (
			<div className="log-text">
				{this.props.content}
			</div>
		)
	}
}

/* TODO unique ids */
class LogBox extends Component {
	lineMarkup (line) {
		return (
			<LogLine key={line.key} content={line.text}/>
		)
	}
	render () {
		return (
			<div className="log-box">
				<div className="log-box-icons">
					<button className="log-box-delete" onClick={this.props.onDelete}/>
					<button className="log-box-options" /*TODO* with this.props.config */ />
				</div>
				<div className="log-box-text-container">
					{this.props.content.map(this.lineMarkup)}
				</div>
			</div>
		)
	}
	shouldComponentUpdate (nextProps) {
		if (nextProps.siblings !== this.props.siblings)
			return true
		return false
	}
}

export default LogBox;
