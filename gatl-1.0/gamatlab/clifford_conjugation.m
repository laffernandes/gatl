function [r] = clifford_conjugation(m)

check_unary_operation_argin

operation = str2func([model_name '_clifford_conjugation']);
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