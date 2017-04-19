function [name params] = ga_active_model(model,varargin)

persistent active_model
persistent active_model_params

% Check the number of input arguments.
if (nargin ~= 0) && (nargin ~= 2) && (nargin ~= 3)
	error('GAToolbox:InputArgumentsCheck','Wrong number of input arguments.')
end

if nargin == 0
    if isempty(active_model)
        % The peace of code below requests user input to change the active specialized geometric algebra model.
        reply = lower(input('There is no active geometric algebra model. Do you want to set one? Y/N [Y]: ','s'));
        if isempty(reply), reply = 'y'; end

        if strcmp(reply,'y')
            reply = lower(input('Choose a model: [E] Euclidean, [H] Homogeneous, [C] Conformal, [P] Clifford(p,q), [V] Conformal (for Voronoi - it is a hack): ','s'));

            % Clifford algebras of signature [p,q]
            if strcmp(reply,'p')
                model = 'clifford';

                p = int32(input('Choose a ''p'' value for base space dimensions: '));
                if p < 1
                    error('GAToolbox:InputArgumentsCheck','Too few ''p'' base space dimensions.')
                end

                q = int32(input('Choose a ''q'' value for base space dimensions: '));
                if q < 0
                    error('GAToolbox:InputArgumentsCheck','Too few ''q'' base space dimensions.')
                end

                % Set active model.
                active_model = sprintf('ga%dp%dq',p,q);
                active_model_params = {model p q};

            % Other geometric algebra models.
            else
                switch reply
                    case 'c'
                        model = 'conformal';
                        mnemonic = 'c';
                    case 'cv'
                        model = 'conformal_voronoi';
                        mnemonic = 'cv';
                    case 'e'
                        model = 'euclidean';
                        mnemonic = 'e';
                    case 'h'
                        model = 'homogeneous';
                        mnemonic = 'h';
                    otherwise
                        error('GAToolbox:InputArgumentsCheck','Unknown geometric algebra model for ''%s''.\nPlease, use ''clifford'', ''euclidean'', ''homogeneous'', ''conformal'', or ''conformal_voronoi''.',upper(reply))
                end

                base_space_dims = int32(input('Choose the number of dimensions of the base space: '));
                if base_space_dims < 1
                    error('GAToolbox:InputArgumentsCheck','Too few base space dimensions.')
                end

                % Set active model.
                active_model = sprintf('ga%d%s',base_space_dims,mnemonic);
                active_model_params = {model base_space_dims};
            end
        end
    end
else
    % The peace of code below uses input arguments to change the active specialized geometric algebra model.
    model = lower(char(model));
    
    % Clifford algebras of signature [p,q]
    if strcmp(model,'clifford')

        if nargin == 2
            p = int32(varargin{1});
            q = int32(0);
        elseif nargin == 3
            p = int32(varargin{1});
            q = int32(varargin{2});
        end

        if p < 1
            error('GAToolbox:InputArgumentsCheck','Too few ''p'' base space dimensions.')
        end

        if q < 0
            error('GAToolbox:InputArgumentsCheck','Too few ''q'' base space dimensions.')
        end

        % Set active model.
        active_model = sprintf('ga%dp%dq',p,q);
        active_model_params = {model varargin{:}};

    % Other geometric algebra models.
    else
        switch model
            case 'conformal'
                mnemonic = 'c';
            case 'conformal_voronoi'
                mnemonic = 'cv';
            case 'euclidean'
                mnemonic = 'e';
            case 'homogeneous'
                mnemonic = 'h';
            otherwise
                error('GAToolbox:InputArgumentsCheck','Unknown geometric algebra model name ''%s''.\nPlease, use ''clifford'', ''euclidean'', ''homogeneous'', ''conformal'', or ''conformal_voronoi''.',model)
        end

        if nargin == 2
            base_space_dims = int32(varargin{1});
            if base_space_dims < 1
                error('GAToolbox:InputArgumentsCheck','Too few base space dimensions.')
            end

            % Set active model.
            active_model = sprintf('ga%d%s',base_space_dims,mnemonic);
            active_model_params = {model varargin{:}};
        else
            error('GAToolbox:InputArgumentsCheck','Wrong number of input arguments.')
        end
    end
end

% Check active geometric algebra model.
if isempty(active_model)
    error('GAToolbox:NoActiveModel','There is no active geometric algebra model.')
end

% Set output argument.
if nargout == 1
    name = active_model;
elseif nargout == 2
    name = active_model;
    params = active_model_params;
elseif (nargout == 0) && (nargin == 0)
    name = active_model;
end