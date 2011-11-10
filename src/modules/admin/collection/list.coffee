fs = require 'fs'

module.exports = () ->
    fs.readFile '.inv/collections.json', (err, data) ->
        throw err if err

        collections = JSON.parse data

        for name, properties of collections
            console.log name + ': ' + properties.join(', ')