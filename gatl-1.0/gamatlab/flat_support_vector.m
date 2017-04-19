function [r] = flat_support_vector(m,tol)

check_unary_operation_argin_tol

operation = str2func([model_name '_flat_support_vector']);
try
    r = multivector(operation(m,tol));
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end