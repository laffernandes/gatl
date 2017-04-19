function [r] = ni()

persistent const

model_name = ga_active_model;

if ~isempty(const) && strcmp(model(const),model_name)
    r = const;
else
    r = [];

    consts = str2func([model_name '_consts']);
    try
       global_consts = consts();
    catch err
        switch err.identifier
            case 'MATLAB:UndefinedFunction'
                error('GAToolbox:UndefinedModel',['Geometric algebra model ''' model_name ''' was not compiled.'])
            otherwise
                rethrow(err);
        end
    end

    for i=1:length(global_consts)
        if strcmp(global_consts(i).name,'ni')
            r = multivector(global_consts(i).value);
        end
    end
    const = r;

    if isempty(r)
        error('GAToolbox:UndefinedFunction','The active geometric algebra model does not define this global constant value.')
    end
end
