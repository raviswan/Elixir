defmodule Discuss.AuthController do
	use Discuss.Web, :controller
	plug Ueberauth
	#alias Discuss.User

	def callback(%{assigns: %{ueberauth_auth: auth}} = conn, params) do
		IO.inspect(conn.assigns)
		user_params = %{token: auth.credentials.token, email: auth.info.email, provider: "github"}
		#the call below goes to the model
		changeset = Discuss.User.changeset(%Discuss.User{}, user_params)
		signin(conn, changeset)
		
	end

	defp signin(conn, changeset) do
		case insert_or_update_user(changeset) do
			{:ok, user} ->
				conn
				|> put_flash(:info, "Welcome back")
				# The cookie is stored below handled by phoneix
				|> put_session(:user_id, user.id)
				|> redirect(to: topic_path(conn, :index))


			{:error, _reason} ->
				conn
				|> put_flash(:error , "error signing in")
				|> redirect(to: topic_path(conn, :index))

		end
	end


	defp insert_or_update_user(changeset) do
		case Repo.get_by(Discuss.User, email: changeset.changes.email) do
			nil ->
				Repo.insert(changeset)
			user -> 
				{:ok, user}

		end
	end
end