unless process.argv[2] and process.argv[3]
    console.log 'Usage: inv[admin] :module :action ...'
    process.exit 1

GLOBAL._ = require 'underscore'

GLOBAL.DataType =
    String: 'String'
    Number: 'Number'
    Function: 'Function'

GLOBAL.validatePropertyValue = (property, value) ->
    parsed = null
    switch property.type
        when DataType.Number
            parsed = parseFloat(value)
            if _.isNaN parsed
                console.log value + ' is not a number'
                process.exit 1
        else parsed = value
    
    return parsed

try
    eval 'require("./' + process.argv[2] + '/' + process.argv[3] + '/' + process.argv[4] + '")(' + _.map(process.argv[5...process.argv.length], (arg) -> '"' + arg + '"').join(', ') + ')'
catch err1
    try
        eval 'require("./' + process.argv[2] + '/' + process.argv[3] + '")(' + _.map(process.argv[4...process.argv.length], (arg) -> '"' + arg + '"').join(', ') + ')'
    catch err2
        throw err2
        console.log 'unknown module'
        process.exit 1