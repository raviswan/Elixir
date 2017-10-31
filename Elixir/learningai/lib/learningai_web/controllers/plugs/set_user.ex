defmodule LearningaiWeb.Plugs.SetUser do
  use LearningaiWeb, :controller
  alias Learningai.User
  alias Learningai.Repo


  def init(_params) do
  end

  # params below is return value from init function above. Typically some expensive
  # operation is done inside init. as init is just done once
  def call(conn, _params) do
    user_id = get_session(conn, :user_id)
    cond do
        user = user_id && Repo.get(User, user_id) ->
            assign(conn, :user, user)
        true ->
            assign(conn, :user, nil)
    end
  end
  
end