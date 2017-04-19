function [r] = basis_vectors(index)

persistent const

model_name = ga_active_model;

if isempty(const) || (~strcmp(model(const),model_name))
    consts = str2func([model_name '_consts']);
    try
       global_consts = consts();
       const = multivector(cell2mat({global_consts(cell2mat({global_consts.is_basis_vector})).value}'));
    catch err
        switch err.identifier
            case 'MATLAB:UndefinedFunction'
                error('GAToolbox:UndefinedModel',['Geometric algebra model ''' model_name ''' was not compiled.'])
            otherwise
                rethrow(err);
        end
    end

    if isempty(const)
        error('GAToolbox:UndefinedFunction','The active geometric algebra model does not define basis vectors.')
    end
end

if nargin == 1
    r = const(index);
else
    r = const;
end