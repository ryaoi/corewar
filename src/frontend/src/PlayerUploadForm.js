import React, { Component } from 'react'
import { handleErrors } from './CorewarsApp'
import uuid from 'uuid'
import './style/index.css'
import './style/upload.css'

class PlayerUploadForm extends Component {
	constructor (props) {
		super(props)
		this.state = {files: []}
	}
	addFile (event) {
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
		else if (this.state.files.length  > 4)
		{
			alert("Can't play a game with more than 4 players.")
			return
		}
		else if (this.state.files.length < 2)
		{
			alert("Can't play a game with less than 2 players.")
			return
		}
		const formData = new FormData()
		const parent = this.props.parent

		this.state.files.map((file, i) => formData.append("file" + i, file))
		fetch('http://localhost:3000/AJAX/game_start', {
			method: "POST",
			body: formData
		}).then(handleErrors)
		.then((response) => response.text())
		.then(parent.gameStarted.bind(parent))
		.catch(e => console.log(e))
	}
	renderFile (item) {
		if (!item.unique_file_key)
			item.unique_file_key = uuid.v4()
		return (
			<div className="file-name" key={item.unique_file_key}>
				{item.name}
			</div>
		)
	}
	render () {
		return (
			<div className="upload-form">
				<div className="upload-title">
					Title placeholder<br/>
					Upload your files here:
				</div>
				<div className="files-list">
					{this.state.files.map(this.renderFile)}
				</div>
				<div className="upload-button">
					<label htmlFor="upload-champion">
						Upload champion:<br/>
					</label>
					<input type="file" name="upload-champion" onChange={this.addFile.bind(this)} multiple />
				</div>
				<span className="champ-buttons">
					<button name="reset-champions" onClick={this.resetFiles.bind(this)}>Reset champions</button>
					<button name="send-champions" onClick={this.sendFiles.bind(this)}>Send champions</button>
				</span>
			</div>
		)
	}
}

export default PlayerUploadForm;
