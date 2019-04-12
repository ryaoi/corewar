import { combineReducers } from "redux"
import uuid from 'uuid'

const initial_state = {
	log_boxes: [],
	log_lines: []
}

const default_config = [1] /* TODO */

function logBoxReducer (state = [], action) {
	var newState = [...state]
	switch (action.type) {
		case 'ADD_LOG_BOX':
			var new_config = default_config
			new_config.key = uuid.v4()
			newState.push(new_config)
			break;
		case 'DELETE_LOG_BOX':
			newState.splice(action.index, 1)
			break;
		default:
	}
	return newState
}

function logLinesReducer(state = [], action) {
	var newState = [...state]
	switch (action.type) {
		case 'ADD_LINES':
			var input_keys = action.input.map((line) => {
				var newLine = line
				newLine.key = uuid.v4()
				return (newLine)
			})
			newState.push(...input_keys)
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
