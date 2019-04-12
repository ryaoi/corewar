import { combineReducers } from "redux";

const initial_state = {
	log_boxes: [],
	log_lines: []
}

const default_config = [1] /* TODO */

function logBoxReducer (state = [], action) {
	var newState = [...state]
	switch (action.type) {
		case 'ADD_LOG_BOX':
			newState.push(default_config)
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
			newState.push(...action.input)
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
