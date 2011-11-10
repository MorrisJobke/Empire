fs = require 'fs'

module.exports = (name, value) ->
    unless name? and value?
        console.log 'Usage: inv property add :name :value'
        process.exit 1
    
    fs.readFile '.inv/properties.json', (err, data) ->
        throw err if err

        properties = JSON.parse data

        unless properties[name]
            console.log 'property ' + name + ' does not exist'
            process.exit 1
        
        property = properties[name]

        parsed = validatePropertyValue property, value
        
        fs.writeFile '.inv/' + name, parsed.toString(), (err) ->
            throw err if err
            console.log 'successfully added property ' + name + ' with value ' + parsed