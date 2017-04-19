function [r] = point(varargin)

check_builder_operation_argin

operation = str2func([model_name '_point']);
try
    r = multivector(operation(coords));
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end