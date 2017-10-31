defmodule LearningaiWeb.AuthController do
  use LearningaiWeb, :controller
  plug Ueberauth

  alias Learningai.User
  alias Learningai.Repo
  


  def callback(%{assigns: %{ueberauth_auth: auth}} = conn, %{"provider" => provider} = _params) do
    user_params = %{token: auth.credentials.token, first_name: auth.info.first_name, last_name: auth.info.last_name, email: auth.info.email, provider: provider}
    changeset = User.changeset(%User{}, user_params)
    signin(conn, changeset)
  end

  defp signin(conn, changeset) do
        case insert_or_update_user(changeset) do
            {:ok, user} ->
                conn
                |> put_flash(:info, "Welcome back")
                # The cookie  stored below as K-V pair is handled by phoneix. The value is encrypted
                |> put_session(:user_id, user.id)
                |> redirect(to: course_path(conn, :index))
            {:error, _reason} ->
                conn
                |> put_flash(:error , "error signing in")
                |> redirect(to: course_path(conn, :index))

        end
    end


    defp insert_or_update_user(changeset) do
        case Repo.get_by(User, email: changeset.changes.email) do
            nil ->
                IO.puts("+++++++++++++")
                IO.inspect(changeset)
                Repo.insert(changeset)
            user -> 
                {:ok, user}

        end
    end

end