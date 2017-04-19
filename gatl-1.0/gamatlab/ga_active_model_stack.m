function ga_active_model_stack(operation)

persistent stack

% Check the number of input arguments.
if (nargin ~= 1)
	error('GAToolbox:InputArgumentsCheck','Wrong number of input arguments.')
end

operation = char(operation);

% Perform requested operation.
switch lower(operation)
    % Add active model into the model's stack.
    case 'push'
        try
            [current_model current_params] = ga_active_model();
            if ~iscell(current_params)
                current_params = {current_params};
            end

            stack = [stack struct('index',{numel(stack)+1},'model',{current_model},'params',{current_params})];
        catch err
            if strcmp(err.identifier,'GAToolbox:NoActiveModel')
                stack = [stack struct('index',{numel(stack)+1},'model',{[]},'params',{[]})];
            else
                rethrow(err)
            end
        end
    
    % Remove the current top model from the stack and set it as the active geometric algebra model.
    case 'pop'
        if isempty(stack)
            error('GAToolbox:ModelStackUnderflow','There is no geometric algebra model into active model''s stack (stack underflow).')
        end
        
        if ~isempty(stack(end).model)
            ga_active_model(stack(end).params{:})
        end
        
        stack = stack(1:end-1);
        
	% Print stack.
    case 'query'
        disp(' ')
        if isempty(stack)
            disp(sprintf('     Empty active model''s stack.\n'))
        else
            for i=1:numel(stack)
                disp(stack(i))
            end
        end
        
    % Retrieve current stack.
    otherwise
        error('GAToolbox:InputArgumentsCheck','Unknown stack operation ''%s''.',operation)
end