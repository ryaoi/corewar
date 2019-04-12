import React, { Component } from 'react'
import { connect } from 'react-redux'
import uuid from 'uuid'
import LogBox from './LogBox'
import './style/index.css'
import './style/game.css'

class LogBar extends Component {
	logBox (box, index) {
		/* TODO move key up to store */
		if (!box.unique_list_key)
			box.unique_list_key = uuid.v4()
		return (
			<LogBox config={box.config} content={box.logs} key={box.unique_list_key} onDelete={() => this.props.deleteLogBox(index)}/>
		)
	}
	render () {
		return (
			<div className="log-bar">
				{this.props.log_boxes.map(this.logBox.bind(this))}
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
		 logs: state.log_lines.filter((line) => doesLogMatch(line, box), state),
		 config: box
		}))
	return {log_boxes: new_log_contents}
}

const LogBarContainer = connect(
	mapStateToProps,
	(dispatch) => ({
		addLogBox: () => dispatch({type: 'ADD_LOG_BOX'}),
		deleteLogBox: (index) => dispatch({type: 'DELETE_LOG_BOX', 'index': index})
	})
)(LogBar)

export default LogBarContainer
