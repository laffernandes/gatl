function [r] = metric()

persistent const

model_name = ga_active_model;

if isempty(const) || ~strcmp(const.model,model_name)
    operation = str2func([model_name '_metric']);
    try
       const = struct('model',{model_name},'matrix',{operation()});
    catch err
        switch err.identifier
            case 'MATLAB:UndefinedFunction'
                error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
            otherwise
                rethrow(err);
        end
    end
end

r = const.matrix;