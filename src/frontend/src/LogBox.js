import React, { Component } from 'react'
import uuid from 'uuid'
import './style/index.css'
import './style/game.css'

class LogLine extends Component {
	render () {
		return (
			<p className="log-line">
				{this.props.content}
			</p>
		)
	}
}

/* TODO unique ids */
class LogBox extends Component {
	lineMarkup (line) {
		if (!line.key)
			line.key = uuid.v4()
		return (
			<LogLine key={line.key} content={line.text}/>
		)
	}
	render () {
		return (
			<div className="log-box">
				<button className="log-box-delete" onClick={this.props.onDelete}/>
				<button className="log-box-options" /*TODO* with this.props.config */ />
				{this.props.content.map(this.lineMarkup)}
			</div>
		)
	}
}

export default LogBox;
