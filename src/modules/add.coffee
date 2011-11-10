fs = require 'fs'

module.exports = (collection, values...) ->
    unless collection? and values.length > 0
        console.log 'Usage: inv add :collection [:value..]'
        process.exit 1
    
    fs.readFile '.inv/collections.json', (err, data) ->
        throw err if err

        collections = JSON.parse data

        unless collections[collection]
            console.log 'collection ' + collection + ' does not exist'
            process.exit 1
        
        if collections[collection].length != values.length
            console.log 'Usage: inv add ' + collection + ' ' + collections[collection].join(', ')
            process.exit 1
        
        fs.readFile '.inv/properties.json', (err, data) ->
            throw err if err

            properties = JSON.parse data

            afterwards = []
            
            for index, name of collections[collection]
                unless properties[name]
                    console.log 'property ' + name + ' does not exist'
                    process.exit 1
                
                validatePropertyValue properties[name], values[index]
            
            fs.mkdir '.inv/' + collection, '0777', (err) ->

                fs.readdir '.inv/' + collection, (err, files) ->

                    fs.mkdir '.inv/' + collection + '/' + files.length, '0777', (err) ->
                        throw err if err

                        for index, name of collections[collection]

                            fs.writeFile '.inv/' + collection + '/' + files.length + '/' + name, values[index], (err) ->
                                throw err if err

            