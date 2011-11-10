fs = require 'fs'

module.exports = (name) ->
    unless name?
        console.log 'Usage: inv property remove :name'
        process.exit 1
    
    fs.unlink '.inv/' + name, (err) ->
        if err
            console.log 'no such property ' + name
        else
            console.log 'successfully deleted property ' + name