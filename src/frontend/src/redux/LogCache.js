
function mergeChannels(channels) {
	var merged = []
	channels.forEach((channel, index) => {
		channel.forEach((line) => merged.push({
			text: line[0],
			key: line[1],
			cycle: line[2],
			type: index
		}))
	})
	merged.sort((a, b) => (a.key - b.key))
	return merged
}

class FilterMatch {
	constructor(block, result) {
		this.block = block
		this.result = result
		this.hit = true
	}
	matches(block) {
		return (block === this.block)
	}
}

var perf = {
	misses: 0,
	matches: 0
}

class FilterCache {
	constructor(size = 10) {
		this.size = size
		this.filters = []
	}
	doFiltering(blocks, filter) {
		var new_matches = []
		blocks.forEach((block) => {
			var match = filter.matches.find((match) => match.matches(block))
			if (!match) {
				var result = block.filter((line) => filter.config.includes(line.type))
				new_matches.push(new FilterMatch(block, result))
				perf.misses++;
			}
			else {
				new_matches.push(match)
				perf.matches++;
			}
		})
		filter.matches = new_matches
		return (filter)
	}
	filter(blocks, config) {
		var filter = this.filters.find((filter) => (filter.config === config))
		if (!filter)
		{
			filter = {
				matches: [],
				'config': config
			}
			if (config.length >= this.size)
				config.shift()
			this.filters.push(this.doFiltering(blocks, filter))
		}
		else {
			this.doFiltering(blocks, filter)
		}
		var merged = []
		filter.matches.forEach((matching_lines) => merged.push(...(matching_lines.result)))
		return (merged)
	}
}

class LogCache {
	constructor(block_size = 250, other) {
		if (!other)
		{
			this.blocks = []
			this.block_size = block_size
			this.filter_cache = new FilterCache()
		}
		else {
			this.copyConstructor(other)
		}
	}
	copyConstructor(other) {
		if (!(other instanceof LogCache))
			throw Error("Tried to create LogCache out of another class")
		this.block_size = other.block_size
		this.filter_cache = other.filter_cache
		this.blocks = []
		if (other.blocks.length)
		{
			other.blocks.forEach((block, index, array) => {
				if (index < (array.length - 1))
					this.blocks.push(block)
			})
			this.blocks.push([])
			other.blocks.slice(-1)[0].forEach((line) => {
				this.blocks.slice(-1)[0].push(line)
			})
		}
	}
	storeSize() {
		if (!this.blocks.length)
			return (0)
		return (
			this.blocks.length * this.block_size + this.blocks.slice(-1)[0].length
		)
	}
	push(log) {
		if (!this.blocks.length
			|| this.blocks.slice(-1)[0].length >= this.block_size)
		{
			this.blocks.push([])
			if (this.blocks.length > 10)
				this.blocks.shift()
		}
		this.blocks.slice(-1)[0].push(log)
	}
	pushLogs(channels) {
		var new_logs = mergeChannels(channels)
		new_logs.forEach((log, index) => {
			this.push(log)
		})
	}
	filterLines(config) {
		/* TODO filter */
		return (
			this.filter_cache.filter(this.blocks, config)
		)
	}
}

export default LogCache
