fs = require 'fs'

module.exports = (name) ->
    unless name?
        console.log 'Usage: invadmin collection remove :name'
        process.exit 1
    
    fs.readFile '.inv/collections.json', (err, data) ->
        throw err if err

        collections = JSON.parse data

        delete collections[name]
        
        fs.writeFile '.inv/collections.json', JSON.stringify(collections), (err) ->
            throw err if err
            console.log 'removed collection ' + name