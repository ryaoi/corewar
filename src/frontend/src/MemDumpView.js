import React, { Component } from 'react'

class MemDumpLine extends Component {
	formatLine (content) {
		if (!content.length || content.length !== 64)
			throw Error("Incorrectly formatted line")
		var output = ""
		for (var index = 0; index < 64; index++)
		{
			output = output + content[index]
			if (index < 63)
				output = output + " "
		}
		return output
	}
	render () {
		return (
			<div className="mem-dump-lime">
				{this.formatLine(this.props.content)}
			</div>
		)
	}
}

class MemDumpView extends Component {
	constructor (props) {
		super(props)
		this.lines = []
		for (var index = 0; index < 64; index++)
		{
			var line = [];
			for (var character = 0; character < 64; character++)
				line.push("00")
			this.lines.push(line)
		}
	}
	render () {
		return (
			<div className="game-mem-dump">
				{this.lines.map((line, index) => <MemDumpLine key={index} content={line}/>)}
			</div>
		)
	}
}

export default MemDumpView
