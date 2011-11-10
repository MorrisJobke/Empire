fs = require 'fs'

module.exports = (name, label, type = DataType.String, map = 0, reduce = 'a + b') ->
    type = type.toLowerCase()
    type = type.charAt(0).toUpperCase() + type.slice(1)
    unless name? and label? and DataType[type]
        console.log 'Usage: invadmin property add :name :label [:type] [:map] [:reduce]'
        console.log 'Types: String, Number, Function'
        process.exit 1
    
    fs.readFile '.inv/properties.json', (err, data) ->
        throw err if err

        properties = JSON.parse data

        if properties[name]
            console.log 'property ' + name + ' already exists'
            process.exit 1
        
        properties[name] =
            label: label
            type: type
        
        if type == DataType.Function
            _.extend properties[name],
                map: map
                reduce: reduce
        
        fs.writeFile '.inv/properties.json', JSON.stringify(properties), (err) ->
            throw err if err
            console.log 'successfully added property ' + label + ' (' + name + ') of type ' + type