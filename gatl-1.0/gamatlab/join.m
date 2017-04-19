function [r] = join(m1,m2,tol)

check_binary_operation_argin_tol

operation = str2func([model_name '_join']);
try
    r = multivector(operation(m1,m2,tol));
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end