fs = require 'fs'

module.exports = (name, propertyNames...) ->
    unless name? and propertyNames.length > 0
        console.log 'Usage: invadmin collection add :name [:property ...]'
        process.exit 1
    
    fs.readFile '.inv/properties.json', (err, data) ->
        throw err if err

        properties = JSON.parse data

        _.each propertyNames, (property) ->
            unless properties[property]
                console.log 'property ' + property + ' does not exist'
                process.exit 1
        
        fs.readFile '.inv/collections.json', (err, data) ->
            throw err if err

            collections = JSON.parse data

            if collections[name]
                console.log 'collection ' + name + ' already exists'
                process.exit 1
        
            collections[name] = propertyNames
            
            fs.writeFile '.inv/collections.json', JSON.stringify(collections), (err) ->
                throw err if err
                console.log 'successfully added collection ' + name