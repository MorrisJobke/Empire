fs = require 'fs'
async = require 'async'

module.exports = (collection, index) ->
    unless collection? and index?
        console.log 'Usage: inv remove :collection :index'
        process.exit 1
    
    reorder = ->
        fs.readdir '.inv/' + collection, (err, files) ->
            for index, file of files
                fs.rename '.inv/' + collection + '/' + file, '.inv/' + collection + '/' + index, (err) ->
                    throw err if err
    
    fs.readdir '.inv/' + collection + '/' + index, (err, files) ->
        throw err if err

        async.parallel _.map(files, (file) -> 
            return (callback) -> fs.unlink '.inv/' + collection + '/' + index + '/' + file, callback
        ), (err) ->
            throw err if err

            fs.rmdir '.inv/' + collection + '/' + index, (err) ->
                throw err if err
                
                reorder()
