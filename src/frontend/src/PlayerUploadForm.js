import React, { Component } from 'react'
import './index.css'
import './upload.css'

class PlayerUploadForm extends Component {
	constructor (props) {
		super(props)
		this.state = {files: []}
	}
	addFile(event) {
		const newFiles = Array.from(event.target.files)

		if (this.state.files.length + newFiles.length > 4)
		{
			alert("Can't play a game with more than 4 players.")
			return
		}
		this.setState(prevState => ({
			files: [...prevState.files, ...newFiles]
		}))
	}
	resetFiles () {
		this.setState({files: []})
	}
	sendFailed() {
		alert('Upload failed')
	}
	sendFiles () {
		if (!this.state.files || !this.state.files.length)
		{
			alert('No champions selected')
			return
		}
		const formData = new FormData()
		const parent = this.props.parent

		this.state.files.map((file) => formData.append(file.name, file))
		fetch('http://localhost:3000/game_start', {
			method: "POST",
			body: formData
		}).then(parent.gameStarted.bind(parent),
			() => alert('Upload failed'))
	}
	renderFile (file) {
		return (
			<div class="file-name">
				{file.name}
			</div>
		)
	}
	render () {
		return (
			<div class="upload-form">
				<div class="upload-title">
					Title placeholder<br/>
					Upload your files here:
				</div>
				<div class="files-list">
					{this.state.files.map(this.renderFile)}
				</div>
				<div class="upload-button">
					<label for="upload-champion">
						Upload champion:<br/>
					</label>
					<input type="file" name="upload-champion" onChange={this.addFile.bind(this)} multiple />
				</div>
				<span class="champ-buttons">
					<button name="reset-champions" onClick={this.resetFiles.bind(this)}>Reset champions</button>
					<button name="send-champions" onClick={this.sendFiles.bind(this)}>Send champions</button>
				</span>
			</div>
		)
	}
}

export default PlayerUploadForm;
