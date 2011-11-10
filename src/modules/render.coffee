fs = require 'fs'
async = require 'async'


module.exports = (template) ->
    unless template?
        console.log 'Usage: inv render :template'
        process.exit 1
    
    fs.readFile '.inv/properties.json', (err, data) ->
        throw err if err

        properties = JSON.parse data


        mapReduce = (path, map, reduce, callback) ->
            list = []
            treebuilder = async.queue ((path, callback) ->
                fs.readdir path, (err, files) ->
                    throw err if err
                    
                    stats = []
                    loading = []

                    _.each files, (file) ->
                        stats.push ((path, file) ->
                            return (callback) ->
                                fs.stat path + '/' + file, (err, stats) ->
                                    throw err if err
                                    
                                    if stats.isDirectory()
                                        treebuilder.push path + '/' + file
                                    else if stats.isFile() and properties[file]
                                        loading.push ((path, file) ->
                                            return (callback) ->
                                                fs.readFile (path + '/' + file), (err, value) ->
                                                    throw err if err
                                                    
                                                    switch properties[file].type
                                                        when DataType.Number
                                                            callback null, 'var ' + file + ' = ' + value + ';'
                                                        when DataType.Function
                                                            callback null
                                                        else
                                                            callback null, 'var ' + file + ' = "' + value + '";'
                                        )(path, file)

                                    callback()
                        )(path, file)
                    
                    async.parallel stats, (err) ->
                        throw err if err

                        async.parallel loading, (err, result) ->
                            throw err if err

                            if result.length > 0
                                ((vars)->
                                    eval vars.join ''
                                    result = null
                                    try
                                        result = eval map
                                    catch err
                                    list.push result if result
                                )(result)

                            callback()
                    
            ), 1

            treebuilder.drain = ->
                result = _.reduce list, (a, b) ->
                    return eval reduce
                callback(null, result)

            treebuilder.push path

        # mapReduce '.inv', 'amount*price', 'a + b', (err, result) ->
        #     console.log result


        inparallel = []

        fs.readFile template, (err, data) ->
            throw err if err

            template = data.toString()

            occurrences = template.match /#\{[a-z]+\.begin\}/ig
            _.each _.uniq(occurrences), (occurrence) ->
                name = occurrence[2...(occurrence.length - 7)]
                
                inparallel.push ((name) ->
                    return (callback) ->
                        fs.readdir '.inv/' + name, (err, files) ->
                            throw err if err

                            re = new RegExp('#\{' + name + '\.begin\}((.|\n)*)#\{' + name + '\.end\}', 'ig');
                            template = template.replace re, (outer, inner) ->
                                result = ''
                                for index, file of _.without files, '.DS_Store'
                                    result += inner.replace /#\{([a-z]+)\}/gi, (outer, inner) ->
                                        return '#{' + name + '/' + index + '/' + inner + '}'

                                return result
                            
                            callback()
                )(name)
            
            async.parallel inparallel, (err) ->
                throw err if err

                occurrences = template.match /#\{[a-z]+(\/[0-9]+\/[a-z]+)?\}/ig
                inparallel = []

                _.each occurrences, (occurrence) ->
                    fullpath = occurrence[2...(occurrence.length - 1)]
                    name = fullpath.match(/([a-z]+\/[0-9]+\/)([a-z]+)/i)
                    if name
                        path = name[1]
                        name = name[2]
                    else
                        name = fullpath
                        path = ''

                    unless properties[name] or properties[name].type != DataType.Function
                        console.log 'property ' + name + ' not defined'
                        process.exit 1
                    
                    if properties[name].type != DataType.Function
                        inparallel.push ((fullpath) ->
                            return (callback) ->
                                fs.readFile '.inv/' + fullpath, (err, value) ->
                                    if err
                                        template = template.replace ('#{' + fullpath + '}'), ''
                                    else
                                        template = template.replace ('#{' + fullpath + '}'), value
                                    callback()
                        )(fullpath)
                    else
                        inparallel.push ((fullpath, path, name) ->
                            return (callback) ->
                                mapReduce '.inv/' + path, properties[name].map, properties[name].reduce, (err, result) ->
                                        template = template.replace ('#{' + fullpath + '}'), result
                                        callback()
                        )(fullpath, path, name)
                
                async.parallel inparallel, (err) ->
                    throw err if err

                    console.log template
                



