import { combineReducers } from "redux"
import uuid from 'uuid'

const initial_state = {
	log_boxes: [],
	log_lines: []
}

const default_config = [0] /* TODO */

function logBoxReducer (state = [], action) {
	var newState = [...state]
	switch (action.type) {
		case 'ADD_LOG_BOX':
			newState.push({
				active_logs: [...default_config],
				key: uuid.v4()
			})
			break;
		case 'DELETE_LOG_BOX':
			newState.splice(action.index, 1)
			break;
		default:
	}
	return newState
}

function prepareLogs(channels) {
	var merged = []
	channels.forEach((channel, index) => {
		channel.forEach((line) => merged.push({
			text: line[0],
			key: line[1],
			cycle: line[2],
			type: index
		}))
	})
	return merged
}

function logLinesReducer(state = [], action) {
	var newState = [...state]
	switch (action.type) {
		case 'ADD_LINES':
			newState.push(...prepareLogs(action.input))
			break;
		/* TODO clean */
		default:
	}
	return newState
}

const rootReducer = combineReducers({
	log_boxes: logBoxReducer,
	log_lines: logLinesReducer
})

export default rootReducer
export { initial_state }
