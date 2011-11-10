fs = require 'fs'

module.exports = (collection) ->
    unless collection?
        console.log 'Usage: inv list :collection'
        process.exit 1
    
    fs.readFile '.inv/collections.json', (err, data) ->
        throw err if err

        collections = JSON.parse data

        unless collections[collection]
            console.log 'collection ' + collection + ' does not exist'
            process.exit 1
    
        fs.readdir '.inv/' + collection, (err, files) ->
            throw err if err

            _.each files, (file) ->
                _.each collections[collection], (name) ->
                    fs.readFile '.inv/' + collection + '/' + file + '/' + name, (err, value) ->
                        throw err if err

                        console.log file + ': ' + name + ' = ' + value