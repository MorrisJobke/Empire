fs = require 'fs'

module.exports = () ->
    fs.readFile '.inv/properties.json', (err, data) ->
        throw err if err

        properties = JSON.parse data

        fs.readdir '.inv', (err, files) ->
            throw err if err
            
            _.each files, (file) ->
                if properties[file]

                    fs.readFile '.inv/' + file, (err, value) ->
                        throw err if err

                        console.log properties[file].label + ' (' + file + ') = ' + value
            