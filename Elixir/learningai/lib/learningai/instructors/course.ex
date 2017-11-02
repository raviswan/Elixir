defmodule Learningai.Instructors.Course do
  use Ecto.Schema
  import Ecto.Changeset
  alias Learningai.Instructors.Course


  schema "courses" do
    field :name, :string
    belongs_to :user, Learningai.User
    timestamps()
  end

  @doc false
  def changeset(%Course{} = course, attrs) do
    course
    |> cast(attrs, [:name])
    |> validate_required([:name])
  end
end
