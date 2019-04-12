import React, { Component } from 'react'
import './style/index.css'
import './style/game.css'

class LogBox extends Component {
	render () {
		return (
			<div className="log-box">
				<button className="log-box-delete" onClick={this.props.onDelete}/>
				<button className="log-box-options" /*TODO* with this.props.config */ />
				{this.props.contents.text}
			</div>
		)
	}
}

export default LogBox;
