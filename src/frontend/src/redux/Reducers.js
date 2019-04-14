import { combineReducers } from 'redux'
import uuid from 'uuid'
import LogCache from './LogCache'

const initial_state = {
	log_boxes: [],
	log_cache: new LogCache(100)
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

function logLinesReducer(state = new LogCache(), action) {
	var newState = new LogCache(state.block_size, state)
	switch (action.type) {
		case 'ADD_LINES':
			newState.pushLogs(action.input)
			break;
		/* TODO clean */
		default:
	}
	return newState
}

const rootReducer = combineReducers({
	log_boxes: logBoxReducer,
	log_cache: logLinesReducer
})

export default rootReducer
export { initial_state }
