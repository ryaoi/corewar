import React, { Component } from 'react'

class MemDumpLine extends Component {
	formatLine(byte, index) {
		return (
			<div className="mem-dump-byte" key={index}>
				{byte}
			</div>
		)
	}
	render () {
		return (
			<div className="mem-dump-lime">
				{this.props.content.map(this.formatLine)}
			</div>
		)
	}
}

class MemDumpView extends Component {
	constructor (props) {
		super(props)
		this.default_dump = []
		for (var index = 0; index < 64; index++) {
			var line = [];
			for (var character = 0; character < 64; character++)
				line.push("00")
			this.default_dump.push(line)
		}
	}
	renderDump() {
		var bytes
		if (!this.props.mem_dump)
			bytes = this.default_dump
		else {
			bytes = []
			for (var line_index = 0; line_index < 64; line_index++) {
				var line = [];
				for (var character = 0; character < 64; character++)
					line.push(this.props.mem_dump.slice(
						line_index * 128 + character * 2,
						line_index * 128 + character * 2 + 2
					))
				bytes.push(line)
			}
		}
		return (
			bytes.map((line, index) => <MemDumpLine key={index} content={line}/>)
		)
	}
	render () {
		return (
			<div className="game-mem-dump">
				{this.renderDump()}
			</div>
		)
	}
}

export default MemDumpView
