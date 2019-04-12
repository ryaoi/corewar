import React, { Component } from 'react'
import { connect } from 'react-redux'
import LogBox from './LogBox'
import './style/index.css'
import './style/game.css'

class LogBar extends Component {
	list () {
		return (
			this.props.logs.map((log, i) => <LogBox config={log.config} contents={log.contents} key={i} onDelete={() => this.props.deleteLogBox(i)}/>)
		)
	}
	render () {
		return (
			<div className="log-bar">
				{this.list()}
				<button className="log-bar-adder" onClick={this.props.addLogBox}/>
			</div>
		)
	}
}

function doesLogMatch(line, config) {
	var match_channels = config.filter((channel) => (line.type === channel))
	if (match_channels.length)
		return true
	return false
}

function mapStateToProps(state) {
	var new_log_contents = state.log_boxes.map((box) => ({
		 contents: state.log_lines.filter((line) => doesLogMatch(line, box), state),
		 config: box
		}))
	return {logs: new_log_contents}
}

const LogBarContainer = connect(
	mapStateToProps,
	(dispatch) => ({
		addLogBox: () => dispatch({type: 'ADD_LOG_BOX'}),
		deleteLogBox: (index) => dispatch({type: 'DELETE_LOG_BOX', 'index': index})
	})
)(LogBar)

export default LogBarContainer
