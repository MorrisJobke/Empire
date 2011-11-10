fs = require 'fs'

module.exports = (name) ->
    unless name?
        console.log 'Usage: invadmin property remove :name'
        process.exit 1
    
    fs.readFile '.inv/properties.json', (err, data) ->
        throw err if err

        properties = JSON.parse data

        delete properties[name]
        
        fs.writeFile '.inv/properties.json', JSON.stringify(properties), (err) ->
            throw err if err
            console.log 'removed property ' + name