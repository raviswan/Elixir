defmodule LearningaiWeb.Router do
  use LearningaiWeb, :router

  pipeline :browser do
    plug :accepts, ["html"]
    plug :fetch_session
    plug :fetch_flash
    plug :protect_from_forgery
    plug :put_secure_browser_headers
    plug LearningaiWeb.Plugs.SetUser

  end

  pipeline :api do
    plug :accepts, ["json"]
  end

  scope "/", LearningaiWeb do
    pipe_through :browser # Use the default browser stack

    get "/", PageController, :index
    resources "/courses", CourseController
  end

  scope "/auth", LearningaiWeb do
    pipe_through :browser
    get "/signout", AuthController, :signout
    # for path /auth/github. the "request" function is defined automatically
     get "/:provider", AuthController, :request
     # for return back from github
     get "/:provider/callback", AuthController, :callback
  end

  # Other scopes may use custom stacks.
  # scope "/api", LearningaiWeb do
  #   pipe_through :api
  # end
end
