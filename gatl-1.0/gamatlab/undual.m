function [r] = undual(m1,m2)

if nargin == 1
    m = m1;
    check_unary_operation_argin

    operation = str2func([model_name '_undual_unary']);
    try
        r = multivector(operation(m));
    catch err
        switch err.identifier
            case 'MATLAB:UndefinedFunction'
                error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
            otherwise
                rethrow(err);
        end
    end
else
    check_binary_operation_argin

	operation = str2func([model_name '_undual_binary']);
    try
        r = multivector(operation(m1,m2));
    catch err
        switch err.identifier
            case 'MATLAB:UndefinedFunction'
                error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
            otherwise
                rethrow(err);
        end
    end
end