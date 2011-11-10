fs = require 'fs'

module.exports = () ->
    fs.readFile '.inv/properties.json', (err, data) ->
        throw err if err

        properties = JSON.parse data

        for name, meta of properties
            console.log '\t' + name + ': ' + meta.label + ' (' + meta.type + ')'