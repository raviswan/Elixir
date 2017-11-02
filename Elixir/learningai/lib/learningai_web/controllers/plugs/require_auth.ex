defmodule LearningaiWeb.Plugs.RequireAuth do
    import Phoenix.Controller  #for using put_flash and redirect
    import Plug.Conn   #for using halt()
    alias LearningaiWeb.Router.Helpers

    def init(_params) do
    
    end

    def call(conn, _params) do
        if conn.assigns[:user] do
            conn
        else
            conn
            |> put_flash(:error, "You must be logged in")
            |> redirect(to: Helpers.course_path(conn, :index))
            |> halt()

        end
    end
end