function [r] = prod(m,dim)

if nargin == 1
    if isvector(m)
        m = m(:);
    end
    dim = 1;
else
    if ~isnumeric(dim) || ~isscalar(dim) || any(dim < 1) || any(dim ~= fix(dim))
        error('GAToolbox:InputArgumentsCheck','Dimension argument must be a positive integer scalar value bigger than zero.')
    end
    
    dim = double(dim);
end

n = ndims(m);

if isscalar(m) || (dim > n)
    r = m;
else
    model_name = model(m);

    operation = str2func([model_name '_gp']);
    try
        order = [dim 1:(dim-1) (dim+1):n];

        m = permute(m,order);
        dims = size(m);

        r = multivector(ones([1 prod(dims(2:end))]));
        for i=1:dims(1)
            r = multivector(operation(r,m(i,:)));
        end
        r = reshape(r,[1 dims(2:end)]);
        r = ipermute(r,order);
    catch err
        switch err.identifier
            case 'MATLAB:UndefinedFunction'
                error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''gp'' or it was not compiled.',model_name)
            otherwise
                rethrow(err);
        end
    end
end