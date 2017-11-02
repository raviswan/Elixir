defmodule Learningai.User do
  use Ecto.Schema
  import Ecto.Changeset

  alias Learningai.User

  schema "users" do
    field :email, :string
    field :first_name, :string  
    field :last_name, :string
    field :provider, :string
    field :token, :string

    has_many :courses, Learningai.Instructors.Course

    timestamps()
  end

  @doc false
  def changeset(%User{} = user, attrs) do
    user
    |> cast(attrs, [:first_name, :last_name, :email, :provider, :token])
    |> validate_required([:email, :provider, :token])
  end
end
